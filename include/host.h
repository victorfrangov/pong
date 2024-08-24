#ifndef HOST
#define HOST

#include <enet/enet.h>

class Host {
public:
	Host() {
        this->_client = NULL;
        this->_peer = NULL;

        ENetAddress address{};

		address.host = ENET_HOST_ANY;
		address.port = 7777;

		this->_server = enet_host_create(&address, 1, 2, 0, 0);

		if (this->_server == NULL) {
			OutputDebugString("An error occurred while trying to create an ENet server host.\n");
			exit(EXIT_FAILURE);
		}
	}

    ENetEvent enetParseEvent() {
        ENetEvent event;
        //supposed to put this in a loop, set the 5000 to 0, because it will delay the game for 5s
        // do we even need _client
        while (enet_host_service(this->_server, &event, 0) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
            {
                std::ostringstream oss;
                oss << "Connected to " << event.peer->address.host << ":" << event.peer->address.port;
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Connection Info", oss.str().c_str(), 0);

                event.peer->data = (void*)"Client info";
                break;
            }
            case ENET_EVENT_TYPE_RECEIVE:
            {
                std::ostringstream oss;
                oss << "Length: " << event.packet->dataLength << "\nData: " << (char*)event.packet->data << "\nFrom: " << (char*)event.peer->data << "\nChannel: " << event.channelID;
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Packet Info", oss.str().c_str(), 0);

                enet_packet_destroy(event.packet);
                break;
            }
            case ENET_EVENT_TYPE_DISCONNECT:
            {
                std::ostringstream oss;
                oss << (char*)event.peer->data << " disconnected";
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Disconnection Info", oss.str().c_str(), 0);

                event.peer->data = NULL;
                break;
            }
            case ENET_EVENT_TYPE_NONE:
                break;
            }
        }
        return event;
    }

    void sendPacket() {
        ENetPacket* packet = enet_packet_create("packet",
            strlen("packet") + 1,
            ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(this->_peer, 0, packet);
    }

    void disconnectPeer() {
        ENetEvent event;
        enet_peer_disconnect(this->_peer, 0);

        while (enet_host_service(this->_client, &event, 3000) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_DISCONNECT:
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Disconnected", "dc", 0);
                return;
            }
        }
        enet_peer_reset(this->_peer);
    }

private:
    ENetHost* _client;
    ENetPeer* _peer;
    ENetHost* _server;
};

#endif /* HOST */