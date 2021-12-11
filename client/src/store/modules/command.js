let socket = WebSocket.prototype // 

const command = {
    state: () => ({
        data: {},
        sending: false,

        responseTime: -1,
        lastPongTime: -1,

        uptime: 0
    }),
    mutations: {
        setData: function (state, data) {
            let objData = JSON.parse(data)
            if (objData.cmd == "pong") {
                state.uptime = objData.stamp

                state.lastPongTime = Date.now()
            } else {

                state.data = { ...state.data, ...objData }
            }

        },
        setSending: function (state, status) {
            state.sending = status
        },
        updateResponseTime: function (state) {
            state.responseTime = 1000 - (Date.now() - state.lastPongTime)
        },
    },
    actions: {
        initCommand: function (context) {
            socket = new WebSocket('ws://' + "192.168.1.13" + ':81')
            // socket = new WebSocket('ws://' + window.location.hostname + ':81');

            socket.addEventListener('message', function (event) {
                context.commit("setData", event.data)
                context.commit("setSending", false)
            });
            socket.addEventListener('open', function () {
                let obj = {
                    cmd: "gal"
                }
                socket.send(JSON.stringify(obj))
                setInterval(() => {
                    context.commit("updateResponseTime")
                    let obj = {
                        cmd: "ping"
                    }
                    if (socket.readyState == WebSocket.OPEN)
                        socket.send(JSON.stringify(obj))
                }, 1000)
            });
        },
        sendCommand: function (context, { espKey, espValue }) {

            if (espValue != undefined)
                espValue = espValue.toString()
            else
                espValue = ""
            let obj = {
                cmd: "exe",
                espKey,
                espValue
            }
            if (socket.readyState == WebSocket.OPEN)
                socket.send(JSON.stringify(obj))
            context.commit("setSending", true)
        },


    },
    getters: {
        getData: function (state) {
            return state.data
        },
        getSending: function (state) {
            return state.sending
        },
        getResponseTime: function (state) {
            return state.responseTime
        },
        getUptime: function (state) {
            return Math.floor(state.uptime / 1000)
        },
    }
}
export default command
