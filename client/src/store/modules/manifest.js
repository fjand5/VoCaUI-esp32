import api from '../../api/http'

const manifest = {
    state: () => ({manifest:  []}),
    mutations: {
        setManifest: function (state, data) {
            state.manifest = data
        },
    },
    actions: {
        requireManifestData: function(context){
            return api.get('api/manifest')   
            .then((data)=>{
                context.commit('setManifest', data)
                return Promise.resolve(true)
            })
        },
    },
    getters: {
        getManifest:function(state){
            return state.manifest
        }
    }
  }
export default manifest
  