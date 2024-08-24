#ifndef CLIENT
#define CLIENT

#include <enet/enet.h>
#include <sstream>

class Client {
public:
	Client() : _client(nullptr), _peer(nullptr){
		this->_client = enet_host_create(NULL, 1, 2, 0, 0);

		if (this->_client == nullptr) {
			OutputDebugString("An error occurred while trying to create an ENet client.\n");
			exit(EXIT_FAILURE);
		}
	}

    Client::~Client() {
        if (_client) {
            enet_host_destroy(_client);
        }
    }

	ENetEvent enetParseEvent() {
		ENetEvent event;
		while (enet_host_service(this->_client, &event, 0) > 0) {
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

    void connectToHost() {
        ENetAddress address;
        ENetEvent event;
        
        enet_address_set_host(&address, "127.0.0.1");
        address.port = 7777;

        this->_peer = enet_host_connect(this->_client, &address, 2, 0);

        if (this->_peer == nullptr) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "No player available", "", 0);
            exit(EXIT_FAILURE);
        }

        if (enet_host_service(this->_client, &event, 3000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Connected", "", 0);
        }
        else {
            enet_peer_reset(this->_peer);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Connection failed", "", 0);
        }
    }

private:
	ENetHost* _client;
    ENetPeer* _peer;
};

#endif /* CLIENT */
