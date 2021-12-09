let socket = WebSocket.prototype // 

const command = {
    state: () => ({
        data: {},
        sending: false,

        responseTime: -1,
        lastPingTime: -1
    }),
    mutations: {
        setData: function (state, data) {
            let objData = JSON.parse(data)
            if (objData.cmd == "pong") {
                let stamp = objData.stamp
                state.responseTime = stamp - state.lastPingTime - 1000
                state.lastPingTime = stamp
                setTimeout(() => {
                    let obj = {
                        cmd: "ping"
                    }
                    if (socket.readyState == WebSocket.OPEN)
                        socket.send(JSON.stringify(obj))
                }, 1000)
            } else {

                state.data = { ...state.data, ...objData }
            }

        },
        setSending: function (state, status) {
            state.sending = status
        },
        setConnectStatus: function (state, status) {
            state.isConnect = status
        },
    },
    actions: {
        initCommand: function (context) {
            socket = new WebSocket('ws://' + "192.168.2.101" + ':81')
            // socket = new WebSocket('ws://' + window.location.hostname + ':81');

            socket.addEventListener('message', function (event) {
                context.commit("setData", event.data)
                context.commit("setSending", false)
            });
            socket.addEventListener('open', function () {
                context.commit("setConnectStatus", true)
                let obj = {
                    cmd: "gal"
                }
                socket.send(JSON.stringify(obj))
                setTimeout(() => {
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
    }
}
export default command
