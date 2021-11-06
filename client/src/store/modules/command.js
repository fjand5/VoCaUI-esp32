let socket = WebSocket.prototype // 

const command = {
    state: () => ({
        data: {},
    }),
    mutations: {
        setData: function (state, data) {
            state.data = { ...state.data, ...JSON.parse(data) }
        }
    },
    actions: {
        initCommand: function (context) {
            // socket = new WebSocket('ws://' + "192.168.2.101" + ':81')
            socket = new WebSocket('ws://'+window.location.hostname+':81');

            socket.addEventListener('message', function (event) {
                context.commit("setData", event.data)
                console.log(event.data)
            });
            socket.addEventListener('open', function () {
                let obj = {
                    cmd: "initValueLed"
                }
                socket.send(JSON.stringify(obj))
            });
        },
        setBrightness: function (context, val) {
            let obj = {
                cmd: "setBrightness",
                val
            }
            if (socket.readyState == WebSocket.OPEN)
                socket.send(JSON.stringify(obj))
        },
        setColor1: function (context, val) {
            let obj = {
                cmd: "setColor1",
                val
            }
            if (socket.readyState == WebSocket.OPEN)
                socket.send(JSON.stringify(obj))
        },
        setColor2: function (context, val) {
            let obj = {
                cmd: "setColor2",
                val
            }
            if (socket.readyState == WebSocket.OPEN)
                socket.send(JSON.stringify(obj))
        },
        setColor3: function (context, val) {
            let obj = {
                cmd: "setColor3",
                val
            }
            if (socket.readyState == WebSocket.OPEN)
                socket.send(JSON.stringify(obj))
        },
        nextMode: function () {
            let obj = {
                cmd: "nextMode"
            }
            if (socket.readyState == WebSocket.OPEN)
                socket.send(JSON.stringify(obj))
        },
        preMode: function () {
            let obj = {
                cmd: "preMode"
            }
            if (socket.readyState == WebSocket.OPEN)
                socket.send(JSON.stringify(obj))
        },


    },
    getters: {
        getMode: function (state) {
            return state.data.mode
        },
        getSpeed: function (state) {
            return state.data.speed
        },
        getBrightness: function (state) {
            return state.data.brightness
        },
        getColor1: function (state) {
            return state.data.color1
        },
        getColor2: function (state) {
            return state.data.color2
        },
        getColor3: function (state) {
            return state.data.color3
        },
    }
}
export default command
