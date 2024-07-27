const socket = new WebSocket("ws://localhost:8765");
var hasConnected = false;

socket.onopen = () => {
   hasConnected = true;
};

socket.onmessage = (event) => {
   console.log(event.data);
};

socket.onclose = () => {
   console.log("connection closed");
};
