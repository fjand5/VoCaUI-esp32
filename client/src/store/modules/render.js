import api from '../../api/http'

const render = {
    state: () => ({render: [
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
            type: "EspSwitch",
            tab: "nhà hàng",
            espKey: "swt_4",
            row: 0,
            props: {
                name: "nút 3",
                round: true,
                span: {
                },
            },
        },
        {
            type: "EspSwitch",
            tab: "nhà hàng",
            espKey: "swt_3",
            row: 0,
            props: {
                name: "nút 3",
                span: {
                },
            },
        },
        {
            type: "EspSwitch",
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
        setRender: function (state, data) {
            state.render = data
        },
    },
    actions: {
        requireRenderData: function(context){
            return api.get('api/render')   
            .then((data)=>{
                console.log(data)
                context.commit('setRender', data)
                return Promise.resolve(true)
            })
        },
    },
    getters: {
        getRender:function(state){
            return state.render
        }
    }
  }
export default render
  