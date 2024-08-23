#ifndef CLIENT
#define CLIENT

#include <enet/enet.h>

class Client {
	Client() {
		ENetHost* client;

		client = enet_host_create(NULL, 1, 2, 0, 0);

		if (client == NULL) {
			OutputDebugString("An error occurred while trying to create an ENet client host.\n");
			exit(EXIT_FAILURE);
		}
	}
};

#endif /* CLIENT */
