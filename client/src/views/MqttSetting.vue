<template>
    <div class="mqtt-setting">
    <el-dialog title="MQTT SETTING" 
    :visible.sync="mqttDialog"
    :append-to-body="true"
    width="90%"
    >
      <el-form 
      label-width="85px"
      v-loading="loading">
          <el-form-item label="Address">
              <el-input v-model="mqtt.addr"></el-input>
          </el-form-item>
          <el-form-item label="Port">
              <el-input v-model="mqtt.port"></el-input>
          </el-form-item>
          <el-form-item label="Username">
              <el-input v-model="mqtt.user"></el-input>
          </el-form-item>
          <el-form-item label="Password">
              <el-input v-model="mqtt.pwd" show-password></el-input>
          </el-form-item>
          <el-divider></el-divider>
          <el-button type="primary" @click="setMqtt">OK</el-button>
      </el-form>
    </el-dialog>
    </div>
  
</template>


<script>
import {mapGetters} from 'vuex'
export default {
    data() {
      return {
        mqttDialog: true,
        loading: true,
        mqtt:{},
      };
    },
    computed:{
      ...mapGetters(['getMqtt'])
    },
    mounted:function(){
      this.$store.dispatch('updateMqtt')
      .then(()=>{
          this.mqtt = this.getMqtt
      })
      .finally(()=>{
        this.loading = false
        console.log(this.getMqtt)
      })
    },
    methods: {
      setMqtt(){
        this.loading = true

        this.$store.dispatch('setMqtt',this.mqtt)
        .finally(()=>{
            this.loading = false
            this.setMqttSuccess();
        })
      },
      setMqttSuccess() {
        this.$destroy()
          this.$notify({
            title: 'Thiết lập MQTT thành công.',
            message: 'Hoàn tất.',
            duration: 10000
          });
      }
    }

}
</script>

<style>

</style>