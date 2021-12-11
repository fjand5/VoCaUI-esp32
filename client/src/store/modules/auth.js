import api from '../../api/http'
const wifi = {
    state: () => ({
        isAuth: false
    }),
    mutations: {
    },
    actions: {
        login: function (context, { username, password }) {
            let basicAuth = 'Basic ' + btoa(username + ':' + password);

            return api.post('/login', {
                headers: { 'Authorization': basicAuth }
            })
                .then((data) => {
                    console.log(data)
                    return Promise.resolve(true)
                })
        },
    },
    getters: {
        getAuthState: function(state){
            return state.isAuth
        }
    }
}
export default wifi
