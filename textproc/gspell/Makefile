# Created by: Olivier Duchateau
# $FreeBSD$

PORTNAME=	gspell
PORTVERSION=	0.1.0
CATEGORIES=	textproc
MASTER_SITES=	GNOME

MAINTAINER=	olivierd@FreeBSD.org
COMMENT=	Spell checking for GTK+

LICENSE=	GPLv2

BUILD_DEPENDS=	valac:${PORTSDIR}/lang/vala \
	iso-codes>=3.57:${PORTSDIR}/misc/iso-codes
LIB_DEPENDS=	libenchant.so:${PORTSDIR}/textproc/enchant

USES=	gmake iconv libtool pathfix pkgconfig tar:xz
USE_GNOME=	glib20 gtksourceview3 introspection:build libxml2
GNU_CONFIGURE=	yes
USE_LDCONFIG=	yes
INSTALL_TARGET=	install-strip

CONFIGURE_ARGS=--enable-introspection=yes \
	--enable-compile-warnings=no \
	--without-html-dir

OPTIONS_DEFINE=	NLS
NLS_USES=	gettext-tools
NLS_CONFIGURE_ENABLE=	nls
OPTIONS_SUB=	yes

.include <bsd.port.mk>
