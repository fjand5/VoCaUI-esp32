<template>
  <div class="login">
    <el-dialog
      title="Đăng nhập"
      :visible.sync="loginDialog"
      :append-to-body="true"
      width="70%"
    >
      <el-form label-width="85px" v-loading="loading">
        <el-form-item label="Username">
          <el-input v-model="username"></el-input>
        </el-form-item>
        <el-form-item label="Password">
          <el-input v-model="password" show-password></el-input>
        </el-form-item>
        <el-divider></el-divider>
        <el-button type="primary" @click="login">OK</el-button>
      </el-form>
    </el-dialog>
  </div>
</template>


<script>
import { mapGetters } from "vuex";

export default {
  data() {
    return {
      loginDialog: false,

      username: "admin",
      password: "12345678",
    };
  },
  computed: {
    ...mapGetters(["getAuthStatus"]),
  },
  watch: {
    getAuthStatus: function (n) {
      this.loginDialog = !n;
    },
  },
  mounted: function () {
    this.$store.dispatch("checkToken")
    .then(()=>{this.$store.dispatch("updateCurrentWifi")})
    .catch(()=>{
      this.loginDialog = true
    })
  },
  methods: {
    login: function () {
      this.$store
        .dispatch("login", { username: this.username, password: this.password })
        .then(() => {
          this.$store.dispatch("updateCurrentWifi");
        })
        .catch(() => {
          this.$notify({
            title: "Không hợp lệ",
            message: "Thông tin đăng nhập không đúng",
            type: "Error",
            duration: 10000,
          });
        });
    },
  },
};
</script>

<style>
</style>