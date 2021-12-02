<template>
  <div class="esp-switch">
    <ComponentWrapper
      :span="props.span"
      :offset="props.offset"
      :pull="props.pull"
      :push="props.push"
    >
      <el-switch
        v-loading="sending"
        element-loading-background="rgba(0, 0, 0, 0.5)"
        @click="sendCommand()"
        >{{ props.name }}</el-switch
      >
    </ComponentWrapper>
  </div>
</template>

<script>
import ComponentWrapper from "./ComponentWrapper.vue";
export default {
  name: "EspSwitch",
  props: {
    props: Object,
  },
  data: function () {
    return {
      sending: false,
    };
  },
  components: {
    ComponentWrapper,
  },
  methods: {
    sendCommand: function () {
      if (this.sending) return;
      this.sending = true;
    },
  },
};
</script>
<style scoped>
</style>
