function connectWebSocket() {
  return {
    messages: [
      "rolling initiative...",
      "generating dungeons...",
      "brewing potions...",
      "seducing the dragon...",
      "casting fireballs...",
      "entering rage...",
      "perceiving... nothing?",
      "disarming traps...",
      "meeting in tavern...",
      "standing night watch...",
      "viciously mocking...",
      "picking pockets...",
      "speaking with animals...",
      "looting bodies...",
      "attuning magic items...",
      "reading spell scrolls...",
      "looting the bodies..."
    ],
    currentMessageIndex: 0,
    currentMessage: "rolling initiative...",
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

