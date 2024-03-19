import WasmModule from "./WasmModule";
import styles from "./page.module.css";

export default function Home() {
  return (
    <main className={styles.main}>
        <WasmModule />
    </main>
  );
}
