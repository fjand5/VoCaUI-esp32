<template>
  <div class="component-wrapper">
    <el-col :xs="24" :span="span">
      <el-card>
        <slot />
      </el-card>
    </el-col>
  </div>
</template>

<script>
export default {
  props: {
    span: Number,
  },
};
</script>

<style scoped>
.el-card{
    background: gray;
}
.el-col {
  margin-bottom: 20px;
}
</style>