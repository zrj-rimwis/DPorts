# Created by: Steve Wills <swills@FreeBSD.org>
# $FreeBSD$

PORTNAME=	shoulda-matchers
PORTVERSION=	3.0.0
CATEGORIES=	devel rubygems
MASTER_SITES=	RG

MAINTAINER=	ruby@FreeBSD.org
COMMENT=	Making tests easy on the fingers and eyes

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/MIT-LICENSE

RUN_DEPENDS=	rubygem-activesupport4>=4.0.0:${PORTSDIR}/devel/rubygem-activesupport4

NO_ARCH=	yes
USE_RUBY=	yes
USE_RUBYGEMS=	yes
RUBYGEM_AUTOPLIST=	yes
USES=		shebangfix

SHEBANG_FILES=	script/*

.include <bsd.port.mk>
