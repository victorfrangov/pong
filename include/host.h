#ifndef HOST
#define HOST

#include <enet/enet.h>

#include <iostream>
#include <string>
#include <map>
//#include <memory>

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

class Host {
public:
	Host() {
        ENetAddress address{};

		address.host = ENET_HOST_ANY;
		address.port = 7777;

		ENetHost* server = enet_host_create(&address, 1, 2, 0, 0);

		if (server == NULL) {
            #ifdef _MSC_VER
			OutputDebugString("An error occurred while trying to create an ENet server host.\n");
            #endif
            std::cout << "Server init failed" << std::endl;
			exit(EXIT_FAILURE);
		}
        this->_server = std::unique_ptr<ENetHost, decltype(&enet_host_destroy)>(server, &enet_host_destroy);
	}

    void parseData(ENetPeer* peer, int id, char* data) {
        std::cout << "BEFORE PARSING: " << data << "\n";

        int data_type;
        sscanf_s(data, "%d|", &data_type);
        switch (data_type) {
            case 1:
            {
                char msg[80]; //msg that was sent
                sscanf_s(data, "%*d|%[^|]", &msg);

                char send_data1[1024] = { '\0' };
                sprintf_s(send_data1, "1|%d|%s", id, msg);
                sendPacket(peer, send_data1);
                break;
            }
            case 2:
            {
                char username[80];
                sscanf_s(data, "2|%[^\n]", &username);

                char send_data2[1024] = { '\0' };
                sprintf_s(send_data2, "2|%d|%s", id, username);
                std::cout << "SEND: " << send_data2 << "\n";


                sendPacket(peer, send_data2);
                client_map[id]->setUsername(username);
                break;
            }
            }
    }

    void update() {
        ENetEvent event;
        int playerID = 0;
        while (true) {
            // gamee loop
            while (enet_host_service(this->_server.get(), &event, 0) > 0) {
                switch (event.type) {
                case ENET_EVENT_TYPE_CONNECT:
                {
                    for (auto const& x : client_map) { //send packets to every client with username data
                        char send_data[1024] = { '\0' };
                        sprintf_s(send_data, "2|%d|%s", x.first, x.second->getUsername().c_str());
                        sendPacket(event.peer, send_data);
                    }

                    playerID++;
                    client_map[playerID] = std::make_unique<ClientData>(playerID); // where do we send username to client?
                    event.peer->data = client_map[playerID].get();

                    char data_to_send[126] = { '\0' }; //sent to client
                    sprintf_s(data_to_send, "3|%d", playerID); // send username to client here
                    sendPacket(event.peer, data_to_send);
                    break;
                }
                case ENET_EVENT_TYPE_RECEIVE:
                {
                    printf("length: %zu, data:  %s.\n", event.packet->dataLength, event.packet->data);

                    parseData(event.peer, static_cast<ClientData*>(event.peer->data)->getID(), reinterpret_cast<char*>(event.packet->data));
                    enet_packet_destroy(event.packet);
                    break;
                }
                case ENET_EVENT_TYPE_DISCONNECT:
                {
                    printf("%x:%u disconnection", event.peer->address.host, event.peer->address.port);
                    char disc_data[126] = { '\0' };
                    sprintf_s(disc_data, "4|%d", static_cast<ClientData*>(event.peer->data)->getID());
                    sendPacket(event.peer, disc_data);

                    event.peer->data = NULL;
                    break;
                }
                }
            }
        }

        enet_host_destroy(this->_server.get());
    }

    void sendPacket(ENetPeer* peer, const char* data) {
        ENetPacket* packet = enet_packet_create(data, strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(peer, 0, packet);
    }

private:
    //ENetHost* _client;
    //ENetPeer* _peer;
    std::map<int, std::unique_ptr<ClientData>> client_map;
    std::unique_ptr<ENetHost, decltype(&enet_host_destroy)> _server{nullptr, &enet_host_destroy};
};

#endif /* HOST */