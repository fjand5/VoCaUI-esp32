<template>
  <div class="esp-button">
    <ComponentWrapper
    :span="props.span"
    >
      <h1>{{ props.name }}</h1>
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
