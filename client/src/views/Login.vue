<template>
  <div class="login">
    <el-dialog
      title="Đăng nhập"
      :visible.sync="loginDialog"
      :append-to-body="true"
      :close-on-click-modal="false"
      :closed="onClose"
      width="70%"
    >
      <el-form
        label-width="85px"
        v-loading="loading"
        element-loading-text="Đang đăng nhập..."
      >
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
// import { mapGetters } from "vuex";

export default {
  data() {
    return {
      loginDialog: true,
      loading: true,
      username: "admin",
      password: "12345678",
    };
  },
  computed: {
    // ...mapGetters(["getAuthStatus"]),
  },
  watch: {
    // getAuthStatus: function (n) {
    //   this.loginDialog = !n;
    // },
  },
  mounted: function () {
    this.loading = true;
    this.$store
      .dispatch("checkToken")
      .then(() => {
        this.$store.dispatch("updateCurrentWifi");
        this.$destroy();
      })
      .catch(() => {})
      .finally(() => {
        this.loading = false;
      });
  },
  methods: {
    onClose: function () {
      this.loginDialog = true;
    },
    login: function () {
      this.loading = true;
      this.$store
        .dispatch("login", { username: this.username, password: this.password })
        .then(() => {
          this.$store.dispatch("updateCurrentWifi");
          this.$destroy();
        })
        .catch(() => {
          this.$notify({
            title: "Không hợp lệ",
            message: "Thông tin đăng nhập không đúng",
            type: "Error",
            duration: 10000,
          });
        })
        .finally(() => {
          this.loading = false;
        });
    },
  },
};
</script>

<style>
</style>