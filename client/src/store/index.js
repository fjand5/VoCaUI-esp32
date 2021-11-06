import Vue from 'vue'
import Vuex from 'vuex'
import wifi from './modules/wifi'
import mqtt from './modules/mqtt'
import system from './modules/system'
import command from './modules/command'

Vue.use(Vuex)

const store = new Vuex.Store({
    modules: [
        wifi,
        mqtt,
        system,
        command
    ]
})
export default store