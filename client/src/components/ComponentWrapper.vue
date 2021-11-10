<template>
  <div class="component-wrapper">
    <el-col 
    :xs="span.xs || 12"
    :sm="span.sm || 12"
    :md="span.md || 8"
    :lg="span.lg || 8"
    :xl="span.xl || 4"
    :offset="offset || 0"
    :pull="pull || 0"
    :push="push || 0"
     >
      <slot />
    </el-col>
  </div>
</template>

<script>
export default {
  props: {
    span: Object,
    offset: Number,
    pull: Number,
    push: Number,
  },
};
</script>

<style scoped>
.el-col {
  margin-bottom: 20px;
}
</style>