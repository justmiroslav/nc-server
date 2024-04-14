#include "SafeFile.hpp"
#include <memory>

std::vector<int> clients;

class Server {
public:
    Server() : safeFile(std::make_unique<SafeFile>()) {
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        serverAddr.sin_addr.s_addr = INADDR_ANY;
    }

    void start() {
        bind(serverSocket, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr));
        listen(serverSocket, SOMAXCONN);
        while (true) {
            int clientSocket = accept(serverSocket, NULL, NULL);
            clientCounter++;
            if (clientCounter == 6) {
                for (auto& client : clients) {
                    close(client);
                }
                break;
            }
            clients.push_back(clientSocket);
            std::thread clientThread(&Server::handleClient, this, clientSocket);
            clientThread.detach();
        }
        close(serverSocket);
    }

    void handleClient(int clientSocket) {
        char buffer[1024];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            if (std::string(buffer) != "Hello") {
                send(clientSocket, "Invalid handshake", 16, 0);
                close(clientSocket);
                return;
            }
            send(clientSocket, "Wait", 4, 0);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            send(clientSocket, "Ready", 5, 0);
            bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived > 0) {
                buffer[bytesReceived] = '\0';
                safeFile->writeToFile(std::string(buffer));
                send(clientSocket, "Ok", 2, 0);
            } else {
                send(clientSocket, "Invalid data", 12, 0);
            }
        }
        close(clientSocket);
    }

private:
    int serverSocket;
    int port = 15000;
    struct sockaddr_in serverAddr{};
    int clientCounter = 0;
    std::unique_ptr<SafeFile> safeFile;
};

int main() {
    Server server;
    server.start();
    return 0;
}