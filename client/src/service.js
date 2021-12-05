import WifiSelector from './views/WifiSelector'
import MqttSetting from './views/MqttSetting'

import store from './store';
let ServicePlugin =
{

  install: function (Vue) {

    Vue.prototype.$showWifiSelector = function () {
      var ComponentClass = Vue.extend(WifiSelector)
      var instance = new ComponentClass({ store: store })
      instance.$mount()
    }
    Vue.prototype.$showMqttSetting = function () {
      var ComponentClass = Vue.extend(MqttSetting)
      var instance = new ComponentClass({ store: store })
      instance.$mount()
    }
    Vue.prototype.$sendCommand = function () {
      let compt = this.compt
      this.$store.dispatch('sendCommand',
        {
          espKey: compt.espKey,
          espValue: this.clientValue
        }
      )
    }
  }
}
export default ServicePlugin