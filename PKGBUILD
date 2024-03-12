# Maintainer: konchin.shih@gmail.com
pkgname=cscript
pkgver=0
pkgrel=1
epoch=
pkgdesc=""
arch=('any')
url="https://github.com/konchinshih/cscript"
license=('GPL')
groups=()
depends=('gcc' 'coreutils' 'bash')
makedepends=()
checkdepends=()
optdepends=()
provides=()
conflicts=()
replaces=()
backup=()
options=()
install=
changelog=
source=("$pkgname-$pkgver.tar.gz")
noextract=()
sha256sums=('75823af272ef75824eca39e58b24e161032a1cff84da9d6f52851c0a8557e4ee')
validpgpkeys=()
BUILDENV+=('!check')

package() {
  cd "$srcdir/src"
	install -Dm755 -d "$pkgdir/usr/bin"
  install -Dm755 "cscript" "$pkgdir/usr/bin/"
	ln -s "/usr/bin/cscript" "$pkgdir/usr/bin/c"
}

