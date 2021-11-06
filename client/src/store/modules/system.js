import api from '../../api/http'

const system = {
    state: () => ({
       
    }),
    mutations: {
    },
    actions: {
        reset: function(){
            return api.get('/api/reset/')
        },
    },
    getters: {
    }
  }
export default system
  