# Created by: Gustau Perez i Querol <gustau.perez@gmail.com>
# $FreeBSD$

PORTNAME=	gnome-shell-extension-filesmenu
PORTVERSION=	0.0.0.20150512
CATEGORIES=	deskutils gnome
DIST_SUBDIR=	gnome3

MAINTAINER=	gnome@FreeBSD.org
COMMENT=	Quickly navigate your file system

BUILD_DEPENDS=	gnome-shell>=0:${PORTSDIR}/x11/gnome-shell \
		gsettings-desktop-schemas>=3.12.0:${PORTSDIR}/devel/gsettings-desktop-schemas
RUN_DEPENDS=	gnome-shell>=0:${PORTSDIR}/x11/gnome-shell \
		gsettings-desktop-schemas>=3.12.0:${PORTSDIR}/devel/gsettings-desktop-schemas

USES=		gettext gmake pkgconfig tar:xz
USE_GNOME=	glib20
CPPFLAGS+=	-I${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib

USE_GITHUB=	yes
GH_ACCOUNT=	bertoldia
GH_PROJECT=	files-menu
GH_TAGNAME=	abb078d

PKGMESSAGE=	../gnome-shell-extra-extensions/pkg-message.slaves

NO_BUILD=	yes

do-install:
		@${MKDIR} ${STAGEDIR}${PREFIX}/share/gnome-shell/extensions/gnome-shell-files-menu
		@cd ${WRKSRC} && ${COPYTREE_SHARE} . \
			${STAGEDIR}${PREFIX}/share/gnome-shell/extensions/gnome-shell-files-menu

.include <bsd.port.mk>
