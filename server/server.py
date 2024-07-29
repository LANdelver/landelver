import asyncio
import websockets
import socket
import json

current_campaign = "demo"

# Function to get the LAN IP address of the current machine
def get_lan_ip():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        # connect() for UDP doesn't send packets
        s.connect(("8.8.8.8", 80))
        ip = s.getsockname()[0]
    except Exception:
        ip = "127.0.0.1"
    finally:
        s.close()
    return ip

async def handle_message(websocket, message):
    json_data = json.loads(message)
    if json_data['type'] == "requestChars":
        packet = '{"type":"requestChars", "chars":["boblin", "clifford"]}'
        await websocket.send(packet)

# Define a callback function to handle incoming WebSocket messages
async def handle_websocket(websocket, path):
    try:
        while True:
            message = await websocket.recv()
            print(f"Received message: {message}")
            await handle_message(websocket, message)

    except websockets.ConnectionClosed:
        pass

if __name__ == "__main__":
    # Start the WebSocket server
    lan_ip = get_lan_ip()
    print(f"Starting websocket server on {lan_ip}:8765")
    start_server = websockets.serve(handle_websocket, lan_ip, 8765)

    asyncio.get_event_loop().run_until_complete(start_server)
    asyncio.get_event_loop().run_forever()
