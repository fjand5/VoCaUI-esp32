import api from '../../api/http'
const wifi = {
    state: () => ({
        isAuth: false,
    }),
    mutations: {
        setToken: function(state, token){
            localStorage.setItem('jwt_aut', token);
        },
        setAuthStatus: function(state, status){
            state.isAuth = status

        },
    },
    actions: {
        login: function (context, { username, password }) {
            let basicAuth = 'Basic ' + btoa(username + ':' + password);

            return api.post('/login', {}, {
                headers: { 'Authorization': basicAuth }
            })
                .then((data) => {
                    let token = data.headers["authorization"]
                    token = token.replace("Bearer ","");
                    context.commit("setToken", token)
                    context.commit("setAuthStatus", true)
                    console.log(token)
                    return Promise.resolve(true)
                })
        },
    },
    getters: {
        getAuthStatus: function(state){
            return state.isAuth
        }
    }
}
export default wifi
