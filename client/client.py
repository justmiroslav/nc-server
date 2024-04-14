import socket, sys

def main():
    ip = sys.argv[1] if len(sys.argv) > 1 else "192.168.56.3"
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((ip, 15000))

    client_socket.sendall(b"Hello")
    while True:
        msg = client_socket.recv(1024)

        if msg.decode("ascii") == "Invalid handshake":
            break
        if msg.decode("ascii") == "Ready":
            user_input = input("Enter a message: ")
            client_socket.sendall(user_input.encode("ascii"))
            msg = client_socket.recv(1024)

            if msg.decode("ascii") == "Ok":
                print("Message sent successfully")
            else:
                print("Failed to send message")

            break

    client_socket.close()

if __name__ == "__main__":
    main()
