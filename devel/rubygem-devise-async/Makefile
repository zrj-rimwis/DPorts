# Created by: Steve Wills <swills@FreeBSD.org>
# $FreeBSD$

PORTNAME=	devise-async
PORTVERSION=	0.10.1
CATEGORIES=	devel rubygems
MASTER_SITES=	RG

MAINTAINER=	ruby@FreeBSD.org
COMMENT=	Send Devise emails in background

LICENSE=	MIT

RUN_DEPENDS?=	rubygem-devise>=3.2:${PORTSDIR}/devel/rubygem-devise

SLAVEDIRS=	devel/rubygem-devise-async-rails4

NO_ARCH=	yes

USE_RUBY=	yes
USE_RUBYGEMS=	yes
RUBYGEM_AUTOPLIST=	yes

.include <bsd.port.mk>
