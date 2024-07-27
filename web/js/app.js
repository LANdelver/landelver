function connectWebSocket() {
  return {
    messages: [
      "Rolling initiative...",
      "Generating dungeons...",
      "Brewing potions...",
      "Seducing the dragon...",
      "Casting fireballs...",
      "Entering rage...",
      "Perceiving... nothing?",
      "Disarming traps...",
      "Meeting in tavern...",
      "Standing night watch...",
      "Viciously mocking...",
      "Picking pockets...",
      "Speaking with animals...",
      "Looting bodies...",
      "Attuning magic items...",
      "Reading spell scrolls...",
      "Looting the bodies..."
    ],
    currentMessageIndex: 0,
    currentMessage: "Rolling initiative...",
    hasConnected: false,
    startLoad() {
      setInterval(() => {
        this.currentMessageIndex = (this.currentMessageIndex + 1) % this.messages.length;
        this.currentMessage = this.messages[this.currentMessageIndex];
      }, 2000);
    },
    connect() {
      const socket = new WebSocket(`ws://${window.location.hostname}:8765`);
      console.log("socket created");
      socket.onopen = () => {
        console.log("connection established");
        this.hasConnected = true;
      };

      socket.onmessage = (event) => {
        console.log(event.data);
      };

      socket.onerror = (error) => {
        console.error('WebSocket error:', error);
        this.reconnect();
      };

      socket.onclose = () => {
        console.log("connection closed");
        this.hasConnected = false;
        this.reconnect();
      };
    },
    reconnect() {
      setTimeout(() => {
        this.connect();
      }, 5000); 
    }
  }
}

function reconnectWebSocket() {

}
