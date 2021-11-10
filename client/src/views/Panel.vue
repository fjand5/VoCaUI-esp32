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
import {mapGetters} from "vuex"
export default {
  data() {
    return {
      selectedTab: "",
    };
  },
  components: {
    EspButton,
  },
  computed: {
    ...mapGetters(['getRender']),
    collectTabs: function () {
      let ret = new Set();
      this.getRender.forEach((elm) => {
        ret.add(elm.tab);
      });
      return ret;
    },
    selectedComponents: function () {
      let ret = this.getRender.filter((elm) => {
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