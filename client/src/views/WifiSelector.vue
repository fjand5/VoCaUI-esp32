<template>
<div class="wifi-selector">
  
  <el-drawer
  :append-to-body="true"
  title="NEAR WIFI"
  :visible.sync="showSelectWifi"
  direction="rtl"
  size="340"
  >    
    <el-table
      v-loading="loading"
      stripe
      :data="getNearWifi"
      style="width: 100%"
      >
      <el-table-column
        width="200"
        label="Wifi">
        <template slot-scope="scope">
          
          {{scope.row.ssid}}
          <i v-if="scope.row.ssid == getCurrentWifi.wifi" class="el-icon-check"></i>
        </template>
      </el-table-column>
      <el-table-column
        width="70"
        prop="rssi"
        label="Sóng">
      </el-table-column>
    
      <el-table-column
      >
        <template v-if="scope.row.ssid != getCurrentWifi.wifi" slot-scope="scope">
          <el-button 
            size="mini"
            type="primary"
            @click="selectWifi(scope.row)"
          > Chọn
          </el-button>
        </template>
      </el-table-column>
      
      </el-table>
  </el-drawer>
  


    <el-dialog
    v-loading="loading"
    :append-to-body="true"
    title="Nhập mật khẩu"
    :visible.sync="showConfirmPassword"
    width="300px">  
      <el-input placeholder="Mật khẩu wifi" v-model="wifiPassword" show-password></el-input>
      <el-divider></el-divider>
      <el-button type="primary" @click="setWifi">OK</el-button>
    </el-dialog>
</div>
  
</template>


<script>
import {mapGetters} from 'vuex'
export default {
    data() {
      return {
        showSelectWifi: true,
        showConfirmPassword: false,

        wifiPassword: undefined,
        wifi: undefined,

        loading: true,

      };
    },
    computed:{
      ...mapGetters(['getNearWifi','getCurrentWifi'])
    },
    mounted:function(){
      this.$store.dispatch('updateNearWifi')
      .finally(()=>{
        this.loading = false
      })
    },
    methods: {
      selectWifi(row){
        this.showConfirmPassword = true;
        this.wifi = row.ssid;
      },
      setWifi(){
        this.$store.dispatch('setWifi',{ssid: this.wifi, sspw: this.wifiPassword})
        .then(()=>{
          this.setWifiSuccess()
        })
        .finally( () => {
          this.showConfirmPassword = false
        })
      },
      
      setWifiSuccess() {
      this.$destroy()
        this.$notify({
          title: 'Thiết lập wifi thành công.',
          message: 'Khởi động lại thiết bị để hoàn tất.',
          duration: 10000
        });
      }
    }

}
</script>

<style>

</style>