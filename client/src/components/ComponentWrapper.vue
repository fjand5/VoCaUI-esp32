<template>
  <div class="component-wrapper">
    <el-col
      :xs="xs"
      :sm="sm"
      :md="md"
      :lg="lg"
      :xl="xl"
      :offset="params.offset || 0"
      :pull="params.pull || 0"
      :push="params.push || 0"
    >
      <slot />
    </el-col>
    <el-col v-if="params.newLine" :span="24"></el-col>
    <el-divider v-if="params.newLine && params.divider"></el-divider>
  </div>
</template>

<script>
export default {
  props: {
    params: Object,
  },
  data: function () {
    return {
      xs: 12,
      sm: 12,
      md: 8,
      lg: 8,
      xl: 4,
    };
  },
  mounted: function () {
    if (!this.params.span) return;
    else if (typeof this.params.span == "number") {
      this.xs = this.params.span;
      this.sm = this.params.span;
      this.md = this.params.span;
      this.lg = this.params.span;
      this.xl = this.params.span;
    } else {
      this.xs = this.params.span.xs || this.xs;
      this.sm = this.params.span.sm || this.sm;
      this.md = this.params.span.md || this.md;
      this.lg = this.params.span.lg || this.lg;
      this.xl = this.params.span.xl || this.xl;
    }
  },
};
</script>

<style scoped>
.el-col {
  margin-bottom: 20px;
  text-align: start;
}
</style>