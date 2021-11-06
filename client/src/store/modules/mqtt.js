import api from '../../api/http'
const mqtt = {
    state: () => ({
        mqtt:{}
    }),
    mutations: {
        setMqtt: function(state, data){
            state.mqtt = data
        }
    },
    actions: {
        updateMqtt: function(context){
            return api.get('/api/getMqtt')
            .then((data)=>{
                context.commit('setMqtt', data)
                return Promise.resolve(true)
            })
        },
        setMqtt: function(context,{addr,port,user,pwd}){
            return api.post('/api/setMqtt',{addr,port,user,pwd})
        }
    },
    getters: {
        getMqtt: function(state){
            return state.mqtt
        }
    }
  }
export default mqtt
  