#ifndef HOST
#define HOST

#include <enet/enet.h>

class Host {
	Host() {
		ENetAddress address;
		ENetHost* server;

		address.host = ENET_HOST_ANY;
		address.port = 7777;

		server = enet_host_create(&address, 1, 2, 0, 0);

		if (server == NULL) {
			OutputDebugString("An error occurred while trying to create an ENet server host.\n");
			exit(EXIT_FAILURE);
		}
	}
};

#endif /* HOST */