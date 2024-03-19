import styles from "./Header.module.css";
import { FC } from "react";

const Header: FC = () => {

    return <header className={styles["header"]}>
        <a className={styles["header__logo"]} href="/">Ludique</a>
        <a className={styles["header__login"]} href="/">Log in</a>
    </header>;
};

export default Header;