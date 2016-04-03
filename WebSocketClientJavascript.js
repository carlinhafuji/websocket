var websocket;

function connect() {
        websocket = new WebSocket("ws://www.websockets.org");
        websocket.onopen = function(evt) { onOpen(evt) };
        websocket.onclose = function(evt) { onClose(evt) };
        websocket.onmessage = function(evt) { onMessage(evt) };
        websocket.onerror = function(evt) { onError(evt) };
}

function disconnect() {
    websocket.close();
}

function doSend(message) {
    websocket.send(message);
}
