import api from '../../api/http'

const render = {
    state: () => ({render:  []}),
    mutations: {
        setRender: function (state, data) {
            state.render = data
        },
    },
    actions: {
        requireRenderData: function(context){
            return api.get('api/render')   
            .then((data)=>{
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
  