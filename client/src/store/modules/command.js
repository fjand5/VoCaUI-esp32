let socket = WebSocket.prototype // 

const command = {
    state: () => ({
        data: {},
        sending: false,
    }),
    mutations: {
        setData: function (state, data) {
            let objData = JSON.parse(data)
            state.data = { ...state.data, ...objData }
        },
        setSending: function (state, status) {
            state.sending = status
        },
    },
    actions: {
        initCommand: function (context) {
            socket = new WebSocket('ws://' + "192.168.2.101" + ':81')
            // socket = new WebSocket('ws://' + window.location.hostname + ':81');

            socket.addEventListener('message', function (event) {
                context.commit("setData", event.data)
                context.commit("setSending", false)
                console.log(event.data)
            });
            socket.addEventListener('open', function () {
                // let obj = {
                //     cmd: "gal"
                // }
                // socket.send(JSON.stringify(obj))
            });
        },
        sendCommand: function (context, { espKey, espValue }) {
            console.log("sendCommand");
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
    }
}
export default command
