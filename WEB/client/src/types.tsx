export interface ITrak {
    name: string;
    genre: string;
    artist: string;
    fileUrl: string;
    guid: string;
    isFav: boolean    
}


export interface IAuthUser {
    login: string
    password: string
}

export interface IDataUser {
    login: string
}

export interface IEditUser {
    newPassword: string
}

export interface IPlaylist {
    playlist: ITrak[]
    current:number
    isPlaying:boolean
}

