# Created by: Jason Bacon <jwbacon@tds.net>
# $FreeBSD$

PORTNAME=	fastx_toolkit
PORTVERSION=	0.0.14
CATEGORIES=	biology

MAINTAINER=	jwbacon@tds.net
COMMENT=	CLI tools for Short-Reads FASTA/FASTQ files preprocessing

LICENSE=	AGPLv3

LIB_DEPENDS=	libgtextutils.so:${PORTSDIR}/biology/libgtextutils

USES=		autoreconf libtool perl5 pkgconfig shebangfix tar:bzip2
USE_PERL5=	run
SHEBANG_FILES=	scripts/*.pl

USE_GITHUB=	yes
GH_ACCOUNT=	agordon
GH_PROJECT=	${PORTNAME}

GNU_CONFIGURE=	yes

CONFIGURE_ENV+=	PKG_CONFIG_PATH=${PREFIX}/lib/pkgconfig

.include <bsd.port.mk>
