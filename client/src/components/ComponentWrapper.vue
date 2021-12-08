<template>
  <div class="component-wrapper">
    <el-col
      :xs="xs"
      :sm="sm"
      :md="md"
      :lg="lg"
      :xl="xl"
      :offset="offset || 0"
      :pull="pull || 0"
      :push="push || 0"
    >
      <slot />
    </el-col>
    <el-col v-if="newLine" :span="24"></el-col>
  </div>
</template>

<script>
export default {
  props: {
    span: [Object, Number],
    offset: Number,
    pull: Number,
    push: Number,
    newLine: Boolean,
    divider: Boolean
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
    if (typeof this.span == "number") {
      this.xs = this.span;
      this.sm = this.span;
      this.md = this.span;
      this.lg = this.span;
      this.xl = this.span;
    } else {
      this.xs = this.span.xs || this.xs;
      this.sm = this.span.sm || this.sm;
      this.md = this.span.md || this.md;
      this.lg = this.span.lg || this.lg;
      this.xl = this.span.xl || this.xl;
    }
  },
};
</script>

<style scoped>
.el-col {
  margin-bottom: 20px;
}
</style>