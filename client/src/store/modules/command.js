let socket = WebSocket.prototype // 

const command = {
    state: () => ({
        data: {},
        sending: false,
        render: [
            {
                type: "EspButton",
                tab: "nhà hàng",
                row: 0,
                espKey: "btn_1",
                props: {
                    name: "nút 1",
                    description: "Bấm vào để bật",
                    span: {

                    },
                },
            },
            {
                type: "EspButton",
                tab: "nhà hàng",
                row: 0,
                espKey: "btn_2",
                props: {
                    name: "nút 2",
                    span: {

                    },
                },
            },
            {
                type: "EspButton",
                tab: "nhà hàng",
                espKey: "btn_3",
                row: 0,
                props: {
                    name: "nút 3",
                    span: {
                    },
                },
            },
            {
                type: "EspButton",
                tab: "bếp",
                row: 0,
                props: {
                    name: "nút 3",
                    span: {
                    },
                },
            },
        ]
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
            socket = new WebSocket('ws://' + "192.168.1.9" + ':81')
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
        getRender: function (state) {
            return state.render
        },
        getSending: function (state) {
            return state.sending
        },
    }
}
export default command
