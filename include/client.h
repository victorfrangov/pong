#ifndef CLIENT
#define CLIENT

#include <enet/enet.h>
#include <sstream>

static int CLIENT_ID = -1;

class ClientData {
public:
    ClientData(int p_id) : _id(p_id) {}

    void setUsername(std::string username) { this->_username = username; }

    int getID() { return this->_id; }

    std::string getUsername() { return this->_username; }
private:
    int _id;
    std::string _username;
};

class Client {
public:
	Client() : _client(nullptr), _peer(nullptr){
		this->_client = enet_host_create(NULL, 1, 2, 0, 0);

		if (this->_client == nullptr) {
            #ifdef _MSC_VER
			OutputDebugString("An error occurred while trying to create an ENet client.\n");
            #endif
			exit(EXIT_FAILURE);
		}
	}

    // Client::~Client() {
    //     if (_client) {
    //         enet_host_destroy(_client);
    //     }
    // }

    void parseData(char* data) {
        int data_type;
        int id;
        sscanf(data, "%d|%d", &data_type, &id);
        switch (data_type) {
        case 1:
            if (id != CLIENT_ID) {
                char msg[80];
                sscanf(data, "%*d|%*d|%[^|]", &msg); //stores the msg itself
            }
            break;
        case 2:
            if (id != CLIENT_ID) {
                char username[80];
                sscanf(data, "%*d|%*d|%[^|]", username);

                client_map[id] = std::make_unique<ClientData>(id);
                client_map[id]->setUsername(username);
            }
            break;
        case 3:
            CLIENT_ID = id;
            break;
        }
    }

    ENetEvent update() {
		ENetEvent event;
		while (enet_host_service(this->_client, &event, 0) > 0) {
            switch (event.type) {
                case ENET_EVENT_TYPE_CONNECT: // WHEN CLIENT CONNECTS, HOST WILL SEND A CONNECT PACKET THAT TELLS USERNAME. CLIENT WILL HAVE HOST NAME IN LOBBY MENU, AFTERWARDS.
                {
                    std::ostringstream oss;
                    oss << "Connected to " << event.peer->address.host << ":" << event.peer->address.port;
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Connection Info", oss.str().c_str(), 0);

                    event.peer->data = (void*)"Client info";
                    break;
                }
                case ENET_EVENT_TYPE_RECEIVE: // RECEIVE HOST MOVEMENT DATA.
                {
                    parseData(reinterpret_cast<char*>(event.packet->data));
                    enet_packet_destroy(event.packet);
                    break;
                }
                case ENET_EVENT_TYPE_DISCONNECT: //DISCONNECTION INFO FROM HOST IF HE QUITS
                {
                    std::ostringstream oss;
                    oss << (char*)event.peer->data << " disconnected";
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Disconnection Info", oss.str().c_str(), 0);

                    event.peer->data = NULL;
                    break;
                }
                default:
                    break;
            }
		}
        return event;
	}

    void disconnectPeer() {
        ENetEvent event;
        enet_peer_disconnect(this->_peer, 0);
        
        while (enet_host_service(this->_client, &event, 3000) > 0) {
            switch (event.type) {
                case ENET_EVENT_TYPE_DISCONNECT:
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Disconnected", "dc", 0);
                    return;
                default:
                    break;
            }
        }
        enet_peer_reset(this->_peer);
    }

    void connectToHost() { // Called when client presses connect (will connect to the ip he chose) if connection success, send to lobby and send/receive connect packets for username info.
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

    void sendPacket(ENetPeer* peer, const char* data) {
        ENetPacket* packet = enet_packet_create(data, strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(peer, 0, packet);
    }

private:
	ENetHost* _client;
    ENetPeer* _peer;

    std::map<int, std::unique_ptr<ClientData>> client_map;
};

#endif /* CLIENT */
