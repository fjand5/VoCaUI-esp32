<template>
  <div class="esp-button">
    <ComponentWrapper
    :span="props.span"
    :description="props.description"
    >
      <el-button>{{ props.name }}</el-button>
    </ComponentWrapper>
  </div>
</template>

<script>
import ComponentWrapper from "./ComponentWrapper.vue";
export default {
  name: "EspButton",
  props: {
    props: Object,
  },
  components: {
    ComponentWrapper,
  },
};
</script>
<style scoped>
</style>
