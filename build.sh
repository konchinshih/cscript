#!/bin/bash

pkgname=$(cat PKGBUILD | awk 'BEGIN{FS="="};{if($1=="pkgname"){print $2}}')
pkgver=$(cat PKGBUILD | awk 'BEGIN{FS="="};{if($1=="pkgver"){print $2}}')

section(){
    echo ">>> $1"
}

section "Copy working directory"
rm -rf "/tmp/$pkgname-$pkgver"
cp -r . "/tmp/$pkgname-$pkgver" || exit 1
cd "/tmp/$pkgname-$pkgver"

section "Generate SRCINFO"
makepkg --printsrcinfo > .SRCINFO

section "Make tarball"
tar -cvzf "$pkgname-$pkgver.tar.gz" .SRCINFO src/* config/*

section "Update checksum"
updpkgsums

section "Make package"
makepkg -scf || exit 1

section "Move built package"
cd - || exit 1
rm *.pkg.tar.zst 2> /dev/null
mv "/tmp/$pkgname-$pkgver"/*.pkg.tar.zst . || exit 1

if [[ -d '/srv/repo/arch' ]]; then
    section "Add to repo"
    sudo repo-add /srv/repo/arch/custom/os/x86_64/custom.db.tar.gz *.pkg.tar.zst
    sudo mv *.pkg.tar.zst /srv/repo/arch/custom/os/x86_64/
fi

section "Clean up"
rm -rf "/tmp/$pkgname-$pkgver"

