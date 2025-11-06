import threading 
import socket  # noqa: F401
import sys
import gzip

directory = "."

def handle_request(client_socket):
    #globa
    global directory
    try:
        while True:
            data = client_socket.recv(1024)
            if not data:
                break
            requested = data.decode()
            keep_alive = True  
            if "Connection: close" in requested.lower():
                keep_alive = False
            if requested.startswith("GET / HTTP/1.1"):
                response  = "HTTP/1.1 200 OK\r\n\r\n"
            elif requested.startswith("GET /echo/"):
                path = requested.split()[1]
                message = path[len("/echo/"):]
                content_length = len(message)
                lines = requested.splitlines()
                header_lines = lines[1:]

                
                accept_encodings = []
                for line in header_lines:
                    if line.lower().startswith("accept-encoding:"):
                        portion = line[len("accept-encoding:"):].strip()
                        accept_encodings = [e.strip() for e in portion.split(",")]
                        break
                
                compressed_body = gzip.compress(message.encode())

                if "gzip" in accept_encodings:
                    headers = (
                        "HTTP/1.1 200 OK\r\n"
                        "Content-Encoding: gzip\r\n"
                        "Content-Type: text/plain\r\n"
                        f"Content-Length: {len(compressed_body)}\r\n"
                        "\r\n"
                    ).encode()
                    response = headers + compressed_body
                    client_socket.sendall(response)
                    continue 
                    
                else:
                    response = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: {content_length}\r\n\r\n{message}"

                    


            elif requested.startswith("GET /user-agent"):
                lines  = requested.splitlines()
                user_agent_val = ""
                for line in lines:
                    if line.lower().startswith("user-agent:"):
                        user_agent_val = line[11:].strip()
                        break
                    else:
                        continue

                user_agent_val_length = len(user_agent_val)
                response = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: {user_agent_val_length}\r\n\r\n{user_agent_val}"




            elif requested.startswith("GET /files/"):
                path = requested.split()[1]
                filename = path[len("/files/"):]
                filepath = f"{directory}/{filename}"
                try:
                    with open(filepath,"rb") as f:
                        content = f.read()
                        length = len(content)
                        headers = (f"HTTP/1.1 200 OK\r\nContent-Type: application/octet-stream\r\nContent-Length:{length} \r\n\r\n")
                        client_socket.sendall(headers.encode() + content)
                        continue
                        
                except FileNotFoundError:
                    response = "HTTP/1.1 404 Not Found\r\n\r\n"
                    client_socket.sendall(response.encode())
                    continue 
            elif requested.startswith("POST /files/"):
                path = requested.split()[1]
                filename = path[len("/files/"):]
                filepath = f"{directory}/{filename}"
                header_body = requested.split("\r\n\r\n")
                

                try:
                    with open(filepath,"wb") as f:
                        content = header_body[1]
                        f.write(content.encode())
                        response = (f"HTTP/1.1 201 Created\r\n\r\n")
                        client_socket.sendall(response.encode())
                        continue
                except Exception as e:
                    print(f"error writing file:{e}")
                    response = "HTTP/1.1 500 Internal Server Error\r\n\r\n"
                    client_socket.sendall(response.encode())
                    continue



            else:
                response  = "HTTP/1.1 404 Not Found\r\n\r\n"
            client_socket.sendall(response.encode())
            if not keep_alive:
                break
    finally:
        client_socket.close()





   


def main():
    global directory 
    print("Logs from the program will appear here!")
    if len(sys.argv) > 2 and sys.argv[1] == "--directory":
        directory = sys.argv[2]

    print(f"Serving files from directory: {directory}")

    
    server_socket = socket.create_server(("localhost", 4221), reuse_port=True)
    try:
        while True:
            print("The Server is running")
            client_socket, addr = server_socket.accept()
            print(f"We have a connection from {addr}")
            t = threading.Thread(target=handle_request, args=(client_socket,))
            t.start()
            
    except KeyboardInterrupt:
        print("Halting Server")
    
    finally:
        server_socket.close()
        print("The server has been shut down")



if __name__ == "__main__":
    main()
