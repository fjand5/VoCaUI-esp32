<template>
  <div class="panel">
    <el-tabs 
    tab-position="top" 
    type="border-card" 
    :stretch="true"
    v-model="selectedTab"
    >
      <template v-for="(tab, index) in collectTabs">
        <el-tab-pane :key="index" :label="tab" :name="tab">
          <el-row :gutter="20">
            <template v-for="(compt, index) in selectedComponents">
              <component
                :key="index"
                :is="compt.type"
                :props="compt.props"
              ></component>
            </template>
          </el-row>
        </el-tab-pane>
      </template>
    </el-tabs>
  </div>
</template>

<script>
import EspButton from "../components/EspButton";
export default {
  data() {
    return {
      selectedTab: "",
      compts: [
        {
          type: "EspButton",
          tab: "nhà hàng",
          props: {
            name: "nút 1",
            description: "Bấm vào để bật",
            span: 24,
          },
        },
        {
          type: "EspButton",
          tab: "nhà hàng",
          props: {
            name: "nút 2",
            span: 12,
          },
        },
        {
          type: "EspButton",
          tab: "bếp",
          props: {
            name: "nút 3",
            span: 12,
          },
        },
      ],
    };
  },
  components: {
    EspButton,
  },
  computed: {
    collectTabs: function () {
      let ret = new Set();
      this.compts.forEach((elm) => {
        ret.add(elm.tab);
      });
      return ret;
    },
    selectedComponents: function () {
      let ret = this.compts.filter((elm) => {
        return elm.tab == this.selectedTab
      });
      return ret;
    },
  },
  mounted: function () {},
  watch: {},
  methods: {},
};
</script>
<style scoped>
</style>