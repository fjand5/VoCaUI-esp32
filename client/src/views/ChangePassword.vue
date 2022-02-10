<template>
  <div class="changePassword">
    <el-dialog
      title="Đổi mật khẩu"
      :visible.sync="changePasswordDialog"
      :append-to-body="true"
      :close-on-click-modal="false"
      width="80%"
    >
      <el-form v-loading="loading">
        <el-form-item label="Password">
          <el-input v-model="password" show-password></el-input>
        </el-form-item>
        <el-form-item label="Mật khẩu mới">
          <el-input v-model="newPassword" show-password></el-input>
        </el-form-item>
        <el-form-item label="Nhập lại mật khẩu mới">
          <el-input v-model="newPassword2" show-password></el-input>
        </el-form-item>
        <el-divider></el-divider>
        <el-button type="primary" @click="changePassword">OK</el-button>
      </el-form>
    </el-dialog>
  </div>
</template>


<script>
export default {
  data() {
    return {
      changePasswordDialog: true,
      loading: false,

      password: "12345678",
      newPassword: "",
      newPassword2: "",
    };
  },
  computed: {},
  watch: {},
  mounted: function () {},
  methods: {
    changePassword: function () {
      if (this.newPassword != this.newPassword2) {
        this.$notify({
          title: "Mật khẩu mới không khớp với nhau",
          message: "Vui lòng kiểm tra lại 2 mật khẩu mới",
          type: "Error",
          duration: 10000,
        });
        return;
      }
      this.loading = true;

      this.$store
        .dispatch("changePassword", {
          password: this.password,
          newPassword: this.newPassword,
        })
        .then(() => {
          this.$store.dispatch("logout");
          this.$store.dispatch("closeWebsocket");
          this.$destroy();
          this.$notify({
            title: "Đổi mật khẩu thành công",
            message: "Mời bạn đăng nhập lại",
            type: "success",
            duration: 10000,
          });
        })
        .catch(() => {
          this.$notify({
            title: "Không hợp lệ",
            message: "Thông tin không đúng",
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