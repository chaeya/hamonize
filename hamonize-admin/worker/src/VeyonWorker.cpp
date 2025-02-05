/*
 * VeyonWorker.cpp - basic implementation of Veyon Worker
 *
 * Copyright (c) 2018-2019 Tobias Junghans <tobydox@veyon.io>
 *
 * This file is part of Veyon - https://veyon.io
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

#include <QCoreApplication>

#include "FeatureWorkerManagerConnection.h"
#include "VeyonConfiguration.h"
#include "VeyonWorker.h"


VeyonWorker::VeyonWorker( const QString& featureUid, QObject* parent ) :
	QObject( parent ),
	m_core( QCoreApplication::instance(),
			QStringLiteral( "FeatureWorker-" ) + VeyonCore::formattedUuid( featureUid ) ),
	m_featureManager(),
	m_workerManagerConnection( nullptr )
{
    vInfo() << "hihoon : Start";
	const Feature* workerFeature = nullptr;

    vInfo() << "hihoon : for loop start";
    for( const auto& feature : m_featureManager.features() )
	{
		if( feature.uid() == featureUid )
		{
			workerFeature = &feature;
		}
	}
    vInfo() << "hihoon : for loop fnished";


	if( workerFeature == nullptr )
	{
		qFatal( "Could not find specified feature" );
	}

    vInfo() << "hihoon : 010 if finished";

	if( m_core.config().disabledFeatures().contains( featureUid ) )
	{
		qFatal( "Specified feature is disabled by configuration!" );
	}

    vInfo() << "hihoon : 020 if finished";

	m_workerManagerConnection = new FeatureWorkerManagerConnection( *this, m_featureManager, featureUid, this );

    vInfo() << "hihoon : 030 if finished";

	vInfo() << "Running worker for feature" << workerFeature->name();
}



bool VeyonWorker::sendFeatureMessageReply( const FeatureMessage& reply )
{
    vInfo() << "hihoon : Start";

    return m_workerManagerConnection->sendMessage( reply );
}
