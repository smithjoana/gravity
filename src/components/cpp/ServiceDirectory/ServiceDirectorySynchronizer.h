/** (C) Copyright 2013, Applied Physical Sciences Corp., A General Dynamics Company
 **
 ** Gravity is free software; you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as published by
 ** the Free Software Foundation; either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public
 ** License along with this program;
 ** If not, see <http://www.gnu.org/licenses/>.
 **
 */

/*
 * ServiceDirectorySynchronizer.h
 *
 *  Created on: Jan 8, 2015
 *      Author: Chris Brundick
 */

#ifndef SERVICEDIRECTORYSYNCHRONIZER__H__
#define SERVICEDIRECTORYSYNCHRONIZER__H__

#include <vector>
#include <queue>
#include <map>
#include <zmq.h>
#include <string>
#include <stdint.h>

#include "GravityDataProduct.h"
#include "protobuf/ServiceDirectoryMapPB.pb.h"
#include "protobuf/ServiceDirectoryRegistrationPB.pb.h"
#include "protobuf/ServiceDirectoryUnregistrationPB.pb.h"

namespace gravity{

typedef struct SyncInitDetails
{
	void* context;
	std::string url;
} SyncInitDetails;

typedef struct SyncDomainDetails
{
	std::string domain;
	std::string ipAddress;
	void* socket;
	int pollItemIndex;
	bool initialized;
	ServiceDirectoryMapPB providerMap;
} SyncDomainDetails;

class ServiceDirectorySynchronizer
{
private:
	void* context;
	std::string ownURL;
	void* commandSocket;
	void* requestSocket;
	std::vector<zmq_pollitem_t> pollItems;
	std::map<std::string, shared_ptr<SyncDomainDetails> > syncMap; // key: domain name
	std::queue<shared_ptr<GravityDataProduct> > registrationUpdates;
	bool pendingResponse;

	void printMap(ServiceDirectoryMapPB providerMap);

	void createRegistrationRequest(std::string productID, std::string url, std::string componentID, std::string domain, 
									ProductChange_RegistrationType type);
	void createUnregistrationRequest(std::string productID, std::string url, ProductChange_RegistrationType type);

public:
	ServiceDirectorySynchronizer(void* context, std::string url);
	virtual ~ServiceDirectorySynchronizer();

	void start();
};
}/* namespace gravity */
#endif //SERVICEDIRECTORYSYNCHRONIZER__H__