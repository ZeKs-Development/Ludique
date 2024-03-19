import { NextFont } from "next/dist/compiled/@next/font";
import styles from "./Header.module.css";
import { Permanent_Marker, Roboto } from "next/font/google";
import { FC } from "react";

const marker: NextFont = Permanent_Marker({ weight: "400", subsets: ["latin"]});
const roboto: NextFont = Roboto({ weight: "400", subsets: ["latin"]});

const Header: FC = () => {

    return <header className={styles["header"]}>
        <a className={`${marker.className} ${styles["header__logo"]}`} href="/home">Ludique</a>
        <nav className={styles["header__nav"]}>
            <a className={`${roboto.className} ${styles["header__nav__link"]}`} href="/home">About</a>
            <a className={`${roboto.className} ${styles["header__nav__link"]}`} href="/home">Community</a>
            <a className={`${roboto.className} ${styles["header__nav__button"]}`} href="/home">Log in</a>
            <a className={`${roboto.className} ${styles["header__nav__button"]}`} href="/home">Register</a>
        </nav>
    </header>;
};

export default Header;