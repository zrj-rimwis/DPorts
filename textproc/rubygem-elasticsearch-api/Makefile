# Created by: Ryan Steinmetz <zi@FreeBSD.org>
# $FreeBSD$
#
# NOTE: This port must be updated at the same time as textproc/rubygem-elasticsearch
# and textproc/rubygem-elasticsearch-transport

PORTNAME=	elasticsearch-api
PORTVERSION=	1.0.13
CATEGORIES=	textproc rubygems
MASTER_SITES=	RG

MAINTAINER=	ruby@FreeBSD.org
COMMENT=	Ruby API for Elasticsearch

LICENSE=	APACHE20

RUN_DEPENDS=	rubygem-multi_json>=0:${PORTSDIR}/devel/rubygem-multi_json

NO_ARCH=	yes
USE_RUBY=	yes
USE_RUBYGEMS=	yes
RUBYGEM_AUTOPLIST=	yes

.include <bsd.port.mk>
