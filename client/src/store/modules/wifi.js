import api from '../../api/http'
const wifi = {
    state: () => ({
        nearWifi: [],
        currentWifi: {}
    }),
    mutations: {
        setNearWifi: function(state, data){
            state.nearWifi = data
        },
        setCurrentWifi: function(state, data){
            state.currentWifi = data
        }
    },
    actions: {
        updateNearWifi: function(context){
            return api.get('/api/scanWifi')
            .then((data)=>{
                context.commit('setNearWifi', data)
                return Promise.resolve(true)
            })
        },
        updateCurrentWifi: function(context){
            return api.post('/api/getWifi')
            .then((data)=>{
                console.log(data)
                context.commit('setCurrentWifi', data)
                return Promise.resolve(true)
            })
        },
        setWifi: function(context,{ssid,sspw}){
            return api.post('/api/setWifi',{ssid,sspw})
        }
    },
    getters: {
        getNearWifi: function(state){
            return state.nearWifi
        },
        getCurrentWifi: function(state){
            return state.currentWifi
        }
    }
  }
export default wifi
  