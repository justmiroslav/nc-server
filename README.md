## Server Setup

To set up the server, follow these steps:

1. Install required dependencies:
  ```bash
  sudo apt-get install -y gcc g++
  ```
2. Clone this repository:
  ```bash
   git clone https://github.com/justmiroslav/nc-server.git
   ```
3. Navigate to the server directory:
  ```bash
   cd nc-server/server/
   ```
4. Compile the server code:
  ```bash
   g++ -o nc_server main.cpp SafeFile.cpp -pthread
   ```
5. Copy the systemd service file to the appropriate directory:
  ```bash
   sudo cp main-server.service /etc/systemd/system/
   ```
6. Reload systemd daemon to apply changes:
  ```bash
   sudo systemctl daemon-reload
   ```
7. Enable the server service to start on boot:
  ```bash
   sudo systemctl enable main-server.service
   ```
8. Start the server service:
  ```bash
   sudo systemctl start main-server.service
   ```

## Client Setup

To connect to the server, follow these steps:

1. Clone this repository:
  ```bash
  git clone https://github.com/justmiroslav/nc-server.git
  ```
2. Navigate to the client directory:
  ```bash
   cd nc-server/client/
   ```
3. Run the client code:
  ```bash
   python3 client.py <ServerContainerIp>
   ```
